<script lang="ts">
  import Battery from './lib/Battery.svelte';
import Display from './lib/Display.svelte';
    import Erase from './lib/Erase.svelte';
    import Tool from './lib/Tool.svelte';
    import Settings from './lib/Settings.svelte';
    import Gallery from './lib/Gallery.svelte';
    import Save from './lib/Save.svelte';
</script>

<main>
  <Battery />
  <div class="flex pt-15 flex-col items-center justify-center font-sans gap-2">
    <p class="text-7xl font-bold text-white">Bit::lace</p>
    <div class="flex flex-row items-center gap-3">
      <img
        src="gluten.svg"
        alt="Glutesha logo"
        class="size-10"
      />
      <p class="text-2xl text-white">By Glutesha Devices</p>
  </div>
  <div class="flex flex-col gap-2 justify-center items-center pb-5">
    <div class="flex flex-col bg-neutral-950 rounded-2xl gap-1 shadow-xl shadow-black/20">
      <Display />
      <Tool />
    </div>
    <div class="flex w-full justify-center items-center gap-2">
      <Save />
      <Erase />
    </div>
      <Gallery />
      <Settings />
  </div>
</main>