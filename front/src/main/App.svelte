<script lang="ts">
  import Display from './lib/Display.svelte';
    import Erase from './lib/Erase.svelte';
    import Settings from './lib/Settings.svelte';
</script>

<main>
  <div class="flex justify-center items-center">
    <Display />
  </div>
  <div class="flex justify-center items-center gap-5 p-5 mr-3">
    <Settings />
    <Erase />
  </div>

</main>