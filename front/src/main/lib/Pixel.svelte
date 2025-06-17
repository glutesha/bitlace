<script lang="ts">
  import { currentTheme } from '../theme';

  export let lit: boolean = false;
  export let onClick: () => void;
</script>

<button aria-label="pixel" onclick={onClick}>
  {#if lit}
    <div class={`${$currentTheme.color} size-9 rounded-full shadow-lg ${$currentTheme.shadow}`}></div>
  {:else}
    <div class="bg-neutral-400 hover:bg-neutral-500 size-9 rounded-full"></div>
  {/if}
</button>